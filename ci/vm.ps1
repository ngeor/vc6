$VBoxManage = "C:\Program Files\Oracle\VirtualBox\VBoxManage.exe"
$VMName = "W2KAgent"
$VMUsername = "Nikolaos Georgiou"
$VMPassword = ""
$GuestFolder = "MySite"
$GuestFolderAbsolute = "C:\$GuestFolder"
$BuildLogFileName = "build.log"
# .e.g .\MySite\build.log
$BuildLog = ".\$GuestFolder\$BuildLogFileName"
# e.g. C:\MySite\build.log
$BuildLogAbsolute = "$GuestFolderAbsolute\$BuildLogFileName"
$SlnInGuest = "$GuestFolderAbsolute\vc6.dsw"
$MSDEV = "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\MSDEV.COM"

function Get-VMState {
    $Lines = $(& $VBoxManage --nologo showvminfo $VMName --machinereadable)
    $Lines = $Lines -split [Environment]::NewLine | where {$_.StartsWith("VMState=")}
    $Lines = $Lines -join "" -split "="
    $Lines[1].Replace('"', '')
}

function Start-VM {
    Write-Host "Starting VM..."
    & $VBoxManage --nologo startvm $VMName --type headless
}

function Close-VM {
    Write-Host "Shutting down VM..."
    # TODO Somehow TeamCity sees the output of poweroff as a warning
    & $VBoxManage --nologo controlvm $VMName poweroff
    & $VBoxManage --nologo snapshot $VMName restorecurrent
}

function Wait-VM {
    sleep 30
    $attempts = 1
    while ($attempts -lt 10) {
        echo "Waiting for VM to be ready, attempt $attempts"
        & $VBoxManage --nologo guestcontrol $VMName stat `
            --username $VMUsername `
            --password `"$VMPassword`" `
            "C:\"
        if ($?) {
            break
        }
        sleep 5
        $attempts++
    }
}

function Copy-IntoVM {
    $attempts = 1
    while ($attempts -lt 10) {
        echo "Copying source into VM, attempt $attempts"
        & $VBoxManage --nologo guestcontrol $VMName copyto `
            --username $VMUsername `
            --password `"$VMPassword`" `
            --recursive `
            --target-directory $GuestFolderAbsolute `
            .
        if ($?) {
            break
        }
        sleep 5
        $attempts++
    }
}

function Run-Build {
    # ignoring errors in case it's a broken build
    # Write-Host instead of echo otherwise it becomes part of the result
    Write-Host "Running build in VM"
    & $VBoxManage --nologo guestcontrol $VMName run `
        --username $VMUsername `
        --password `"$VMPassword`" `
        --wait-stdout `
        --exe $MSDEV `
        -- $MSDEV $SlnInGuest /OUT $BuildLogAbsolute /MAKE ALL /REBUILD | Out-Host
    return $?
}

function Copy-OutOfVM {
    $attempts = 1
    while ($attempts -lt 10) {
        echo "Copying files out of VM, attempt $attempts"
        & $VBoxManage --nologo guestcontrol $VMName copyfrom `
            --username $VMUsername `
            --password `"$VMPassword`" `
            --recursive `
            --target-directory . `
            $GuestFolderAbsolute
        if ($?) {
            break
        }
        sleep 5
        $attempts++
    }
}

function Delete-Folders {
    param (
        [string[]] $Folders
    )
    foreach ($Folder in $Folders) {
        if (Test-Path $Folder) {
            del -Recurse -Force $Folder
        }
    }
}

function Clear-OutputFolder {
    Delete-Folders -Folders $GuestFolder, "x64", "i386", "Debug", "Release"
}

if (Test-Path ".\vc6.dsw") {
    $State = Get-VMState
    if ($State -eq "poweroff") {
        Start-VM
        Clear-OutputFolder
        Wait-VM
        Copy-IntoVM
        $BuildSucceeded = Run-Build
        Copy-OutOfVM
        Close-VM
        if ($BuildSucceeded) {
            cat $BuildLog
        } else {
            Write-Warning "Build failed, please check build log below"
            cat $BuildLog
            Write-Warning "Build failed, please check build log above"
            exit 1
        }
    } else {
        Write-Warning "VM was not powered off, aborting"
        exit 1
        # Close-VM
    }
} else {
    Write-Error "The script must be run from the vc6 folder where vc6.dsw lives"
    exit 1
}
