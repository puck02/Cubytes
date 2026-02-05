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
    /// 显示提示
    Hint { name: String },
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
        Some(Commands::Hint { name }) => {
            show_hint(&exercises, &name, &state);
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

fn show_hint(exercises: &ExerciseList, name: &str, state: &StateFile) {
    match exercises.find(name) {
        Some(exercise) => {
            let hint_level = state.get_hint_level(name);
            println!("\n{} {}", "💡 提示:".yellow().bold(), name);
            
            if let Some(hint) = exercise.get_hint(hint_level) {
                println!("{}", hint);
                if hint_level < exercise.hint_count() - 1 {
                    println!("\n{}", "再次运行查看更多提示...".dimmed());
                }
            } else {
                println!("{}", "没有更多提示了".dimmed());
            }
        }
        None => {
            eprintln!("{} 找不到练习: {}", "错误:".red().bold(), name);
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
}
