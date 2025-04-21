if ([System.Environment]::Is64BitOperatingSystem) {
    Write-Host "Destroying the previous VM..."
    vagrant destroy -f

    Write-Host "Running the benchmark..."
    vagrant up --provider=virtualbox

    Write-Host "Destroying VM after benchmark..."
    vagrant destroy -f
} else {
    Write-Host "This script is intended for an AMD64 architecture. Exiting..."
}
