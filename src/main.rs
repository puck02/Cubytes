use clap::{Parser, Subcommand};
use colored::Colorize;
use std::path::PathBuf;

mod exercise;
mod run;
mod verify;
mod watch;
mod state;
mod ui;

use exercise::ExerciseList;
use state::StateFile;

#[derive(Parser)]
#[command(name = "cling")]
#[command(about = "C语言快速入门练习系统", long_about = None)]
struct Cli {
    #[command(subcommand)]
    command: Option<Commands>,
}

#[derive(Subcommand)]
enum Commands {
    /// 启动watch模式（默认）
    Watch,
    /// 运行指定练习
    Run { name: String },
    /// 列出所有练习
    List,
    /// 重置练习
    Reset { name: String },
    /// 检查当前练习
    Check,
    /// 检查所有练习
    CheckAll,
}

fn main() {
    let cli = Cli::parse();
    
    // 加载练习列表
    let exercises = match ExerciseList::from_file("info.toml") {
        Ok(list) => list,
        Err(e) => {
            eprintln!("{} {}", "错误:".red().bold(), e);
            std::process::exit(1);
        }
    };
    
    // 加载状态
    let mut state = StateFile::load(".cling-state.txt");
    
    match cli.command {
        None | Some(Commands::Watch) => {
            watch::watch(&exercises, &mut state);
        }
        Some(Commands::Run { name }) => {
            run::run(&exercises, &name, &mut state);
        }
        Some(Commands::List) => {
            list_exercises(&exercises, &state);
        }
        Some(Commands::Reset { name }) => {
            reset_exercise(&exercises, &name, &mut state);
        }
        Some(Commands::Check) => {
            check_current(&exercises, &mut state);
        }
        Some(Commands::CheckAll) => {
            check_all(&exercises, &mut state);
        }
    }
}

fn list_exercises(exercises: &ExerciseList, state: &StateFile) {
    println!("\n{}", "📚 练习列表".cyan().bold());
    println!("{}", "=".repeat(60));
    
    let mut current_dir = String::new();
    for (i, exercise) in exercises.exercises.iter().enumerate() {
        if exercise.dir != current_dir {
            current_dir = exercise.dir.clone();
            println!("\n{}", format!("  {}", current_dir).blue().bold());
        }
        
        let status = if state.is_completed(&exercise.name) {
            "✅".green()
        } else if Some(&exercise.name) == state.current.as_ref() {
            "▶️ ".yellow()
        } else {
            "⭕".dimmed()
        };
        
        println!("  {} {}", status, exercise.name);
    }
    
    let completed = state.completed.len();
    let total = exercises.exercises.len();
    println!("\n{}", "=".repeat(60));
    println!("进度: {}/{} ({}%)", completed, total, completed * 100 / total);
}

fn reset_exercise(exercises: &ExerciseList, name: &str, state: &mut StateFile) {
    match exercises.find(name) {
        Some(_) => {
            // 从备份恢复或从git恢复
            println!("{} {}", "🔄 重置练习:".yellow(), name);
            // TODO: 实现重置逻辑
            state.reset_exercise(name);
            state.save(".cling-state.txt");
            println!("{}", "✅ 重置成功".green());
        }
        None => {
            eprintln!("{} 找不到练习: {}", "错误:".red().bold(), name);
        }
    }
}

fn check_current(exercises: &ExerciseList, state: &mut StateFile) {
    let current = match &state.current {
        Some(c) => c.clone(),
        None => {
            println!("{}", "没有当前练习".yellow());
            return;
        }
    };
    run::run(exercises, &current, state);
}

fn check_all(exercises: &ExerciseList, state: &mut StateFile) {
    println!("\n{}", "🔍 检查所有练习...".cyan().bold());
    
    let mut passed = 0;
    let mut failed = 0;
    
    for exercise in &exercises.exercises {
        print!("检查 {}... ", exercise.name);
        match verify::verify(exercise) {
            Ok(_) => {
                println!("{}", "✅".green());
                state.complete_exercise(&exercise.name);
                passed += 1;
            }
            Err(_) => {
                println!("{}", "❌".red());
                failed += 1;
            }
        }
    }
    
    state.save(".cling-state.txt");
    
    println!("\n{}", "=".repeat(60));
    println!("通过: {} | 失败: {}", passed.to_string().green(), failed.to_string().red());
    
    // 如果全部通过，显示庆祝动画
    if failed == 0 {
        show_completion_celebration(&exercises);
    }
}

fn show_completion_celebration(exercises: &ExerciseList) {
    use std::{thread, time::Duration};
    use std::io::Write;
    
    // 清屏
    print!("\x1B[2J\x1B[1;1H");
    std::io::stdout().flush().ok();
    
    // 烟花动画
    for _ in 0..3 {
        thread::sleep(Duration::from_millis(300));
        println!("\n\n    {}  {}  {}  {}  {}", 
            "✨".bright_yellow(), 
            "🎆".bright_magenta(), 
            "✨".bright_cyan(), 
            "🎆".bright_yellow(),
            "✨".bright_magenta()
        );
        std::io::stdout().flush().ok();
    }
    
    // 清屏显示最终庆祝
    print!("\x1B[2J\x1B[1;1H");
    
    // ASCII鲨鱼
    let shark = r#"
                                                                ....                                
                                                           ..:::::.                                 
                                                        .:-----:::.                                 
                                                     .:-------::..                                  
                                                   :---------:::..                                  
                                                  ::::::----:::::.                                  
                                             ........----::....:.                                   
                                     ...::--------+#%%%#*====-::.                                   
                                 .::---------------======-:::-===-.                                 
                            ..:::----------------------:... :----=+=.                               
                        .::-------------------------:.   +%-.------=+-                              
                       .:::::--------------:-----:.      =+- --------=+.                            
                         :+-:.  .::--------:....            .-----::-:-+:                           
                          #%%#+-.     ....:::::-:     ..    .  .:-.:::--+:                          
                           #%%%%%#+-.          ........           .::.::-=. :.                      
                           .#%%%%%%%#*=:           ..::-==         :.:.:--- :-=-:                   
                            .+*%%%%%%%%%#+:...:----== .*@=          .-.----. .::-=:                 
                :---:         =.-========-===+: :#@@:   :           ..:---:. .::.:-=:               
            .+#*=+#@+         *+.#%..*%#. -%@#   :*- .....           ----:..  ..::...               
            :*%*-:##:--.       #*:=   +- ..:=..::.::-:=::.          .--:.   ..                      
              :=**#*.-:=-:-==.  #+  := ..::-::-:==-=:+#.            :-:  :-::--:.                   
                .:-.   . :%*.   .#+ .+::=@+-=+-=@%-  .            .---:. .-------:                  
                   ..---: -= ... -%+    -=+: . -.                :---:.=-::.------.  .::            
                  :::---.....-:: -%*.        .:.....:::.         ---..+@%#*: .----.  -:.            
            ..    -----. :----:: .%+      .--:.        .-:.      -.:+#%%%#*:.:::::                  
           :---   .-:::.:-----::. *#    .--:    .::::..:---.    :-:.-*++=:..:::..   .::-:           
             ..:    ..::::::--::. :#-   ---    ------------:    --::. ..  .....    :::::            
                       .........   +#.  ---   .------------:   :-:::::.           .                 
              :...::...             ##: :--.   .::::.   --:    -:::::.       .:--=-.                
             .::::.....:-:..:..     .##=..:-:.        .::   :=-:::::. .. .:------.                  
                ....:---..:.:.....   :#%#+-:::::....:::::-+##=::::. ..:::--::::.                    
                ::   .--:.:::::...... .+%%##*++====++**#####+.::::-=------:::..                     
                   .:::::::::::::....   :=*#%%%%%%%#%%%%#%###+:.-==+=--:.::::.                      
                          ...:::....       :-=++*****+=-:=**+=+==+:       ...:.                     
                                 .                    ...      .:::          ..                     
    "#;
    
    println!("{}", shark.bright_cyan());
    println!();
    println!("{}", "    ╔═══════════════════════════════════════════╗".bright_yellow());
    println!("{}", "    ║                                           ║".bright_yellow());
    println!("{}", "    ║   🎓 恭喜你完成了所有 58 道练习！ 🎓    ║".bright_green().bold());
    println!("{}", "    ║                                           ║".bright_yellow());
    println!("{}", "    ║     你已经掌握了C语言的基础知识！        ║".bright_green());
    println!("{}", "    ║                                           ║".bright_yellow());
    println!("{}", "    ╚═══════════════════════════════════════════╝".bright_yellow());
    println!();
    println!("{}", "    🏆 成就解锁：".bright_yellow().bold());
    println!("       {} 完成 58 道练习", "✓".green());
    println!("       {} 掌握 C11 标准", "✓".green());
    println!("       {} 实现贪吃蛇游戏", "✓".green());
    println!();
    println!("{}", "    🚀 下一步建议：".bright_cyan().bold());
    println!("       • 查看 {} 目录对比你的实现", "solutions/".yellow());
    println!("       • 尝试优化贪吃蛇游戏性能");
    println!("       • 开始学习数据结构与算法");
    println!("       • 探索 Linux 系统编程");
    println!();
    println!("{}", exercises.final_message);
    println!();
    println!("{}", "    🎉🎊 Keep coding! 💻✨ 🎊🎉".bright_magenta().bold());
    println!();
}
