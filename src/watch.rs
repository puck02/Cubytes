use crate::exercise::ExerciseList;
use crate::state::StateFile;
use crate::verify;
use crate::ui;
use colored::Colorize;
use notify::{Watcher, RecursiveMode, Event};
use std::sync::mpsc::channel;
use std::time::Duration;
use crossterm::event::{self, Event as TermEvent, KeyCode, KeyEvent};

pub fn watch(exercises: &ExerciseList, state: &mut StateFile) {
    println!("\n{}", exercises.welcome_message);
    println!("\n{}", "开始watch模式...".cyan().bold());
    println!("{}", "修改练习文件后会自动检测并运行".dimmed());
    println!("\n{}", "命令: n(next) | r(run) | l(list) | q(quit)".yellow());
    
    // 确定当前练习
    let mut current_exercise = if let Some(current) = &state.current {
        current.clone()
    } else if let Some(first) = exercises.exercises.first() {
        state.set_current(&first.name);
        state.save(".cling-state.txt");
        first.name.clone()
    } else {
        eprintln!("{}", "没有可用的练习".red());
        return;
    };
    
    // 显示进度
    ui::show_progress(exercises, state);
    
    // 初始检查
    check_exercise(exercises, &current_exercise, state);
    
    // 设置文件监控
    let (tx, rx) = channel();
    let mut watcher = notify::recommended_watcher(move |res: Result<Event, _>| {
        if let Ok(event) = res {
            let _ = tx.send(event);
        }
    }).expect("创建watcher失败");
    
    watcher.watch(
        std::path::Path::new("exercises"),
        RecursiveMode::Recursive,
    ).expect("监控目录失败");
    
    // 主循环
    loop {
        // 检查文件变化
        if let Ok(event) = rx.recv_timeout(Duration::from_millis(100)) {
            // 检查是否是当前练习的文件
            if let Some(exercise) = exercises.find(&current_exercise) {
                let path = exercise.path();
                if event.paths.iter().any(|p| p == &path) {
                    println!("\n{}", "检测到文件变化...".yellow());
                    check_exercise(exercises, &current_exercise, state);
                }
            }
        }
        
        // 检查键盘输入
        if event::poll(Duration::from_millis(10)).unwrap_or(false) {
            if let Ok(TermEvent::Key(KeyEvent { code, .. })) = event::read() {
                match code {
                    KeyCode::Char('n') | KeyCode::Char('N') => {
                        if let Some(next) = exercises.get_next(&current_exercise) {
                            current_exercise = next.name.clone();
                            state.set_current(&current_exercise);
                            state.save(".cling-state.txt");
                            println!("\n{}", format!("切换到: {}", current_exercise).cyan());
                            check_exercise(exercises, &current_exercise, state);
                        } else {
                            println!("\n{}", "已经是最后一题了".yellow());
                        }
                    }
                    KeyCode::Char('r') | KeyCode::Char('R') => {
                        println!("\n{}", "重新运行...".cyan());
                        check_exercise(exercises, &current_exercise, state);
                    }
                    KeyCode::Char('l') | KeyCode::Char('L') => {
                        ui::show_progress(exercises, state);
                    }
                    KeyCode::Char('q') | KeyCode::Char('Q') => {
                        println!("\n{}", "退出watch模式...".yellow());
                        break;
                    }
                    _ => {}
                }
            }
        }
    }
}

fn check_exercise(exercises: &ExerciseList, name: &str, state: &mut StateFile) {
    if let Some(exercise) = exercises.find(name) {
        println!("\n{}", "=".repeat(60));
        println!("{} {}", "检查:".cyan().bold(), name);
        
        match verify::verify(exercise) {
            Ok(output) => {
                println!("{}", "✅ 成功！".green().bold());
                if !output.is_empty() && output.len() < 500 {
                    println!("\n{}", output);
                }
                
                if !state.is_completed(name) {
                    state.complete_exercise(name);
                    
                    if let Some(next) = exercises.get_next(name) {
                        println!("\n{}", "🎉 太棒了！进入下一题...".green());
                        state.set_current(&next.name);
                    } else {
                        show_completion_celebration(exercises);
                    }
                    
                    state.save(".cling-state.txt");
                    ui::show_progress(exercises, state);
                }
            }
            Err(e) => {
                println!("{}", "❌ 失败".red().bold());
                
                // 只显示前几行错误
                let lines: Vec<&str> = e.lines().collect();
                for line in lines.iter().take(15) {
                    println!("{}", line);
                }
                if lines.len() > 15 {
                    println!("\n{}", "... (更多错误信息被省略)".dimmed());
                }
            }
        }
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
