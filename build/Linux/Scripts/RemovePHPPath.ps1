# Remove Kotlin path
$path2delete = 'C:\PHP'
$systemPath = [Environment]::GetEnvironmentVariable('Path');
$systemPath = $systemPath.replace($path2delete, '')
$systemPath = $systemPath
[Environment]::SetEnvironmentVariable('Path', $systemPath);

# Clean system variable
$systemPath = [Environment]::GetEnvironmentVariable('Path');
while ($systemPath.contains(';;')) {
    $systemPath = $systemPath.replace(';;', ';')
}
[Environment]::SetEnvironmentVariable('Path', $systemPath);