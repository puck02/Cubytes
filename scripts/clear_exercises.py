#!/usr/bin/env python3
import re
from pathlib import Path

base = Path('/Users/ponepuck/Library/CloudStorage/OneDrive-Personal/workSpace/Cling/exercises')

def clear_function_bodies(filepath):
    """Clear function implementations but keep test functions"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Pattern to match function definitions (excluding test functions, setUp, tearDown, main)
    pattern = r'((?:int|void|char|float|double|size_t)\s+(?!setUp|tearDown|test_|main)\w+\s*\([^)]*\)\s*{)([^}]+)(})'
    
    def replacer(match):
        prefix = match.group(1)
        body = match.group(2)
        suffix = match.group(3)
        
        # If body already has TODO and is mostly empty, skip
        if '// TODO' in body and body.count('\n') <= 3:
            return match.group(0)
        
        # Replace with TODO placeholder
        return f'{prefix}\n    // TODO: 实现这个函数\n    \n{suffix}'
    
    new_content = re.sub(pattern, replacer, content, flags=re.DOTALL)
    
    if new_content != content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(new_content)
        return True
    return False

# Process all .c files
count = 0
for c_file in base.rglob('*.c'):
    # Skip intro exercises
    if 'intro' in str(c_file) or '08_final_project' in str(c_file):
        continue
    
    if clear_function_bodies(c_file):
        rel_path = c_file.relative_to(base.parent)
        print(f'✓ {rel_path}')
        count += 1

print(f'\n✅ Cleared {count} exercise files')
