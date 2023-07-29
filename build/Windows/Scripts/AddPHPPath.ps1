# Add Kotlin Path
$path2add = ';C:\PHP'
$systemPath = [Environment]::GetEnvironmentVariable('Path');
If (!$systemPath.contains($path2add)) {
    $systemPath += $path2add
    $systemPath = $systemPath 
    [Environment]::SetEnvironmentVariable('Path', $systemPath);
}

# Clean system variable
$systemPath = [Environment]::GetEnvironmentVariable('Path');
while ($systemPath.contains(';;')) {
    $systemPath = $systemPath.replace(';;', ';')
}
[Environment]::SetEnvironmentVariable('Path', $systemPath);