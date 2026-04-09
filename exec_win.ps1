# --------------------------------------------------------
# exec_win.ps1
#
# Description: Verifica, baixa e configura ferramentas, dependências
#              , compila e roda o projeto no windows 
# Autor: Deepseek
# Version: 1.0
# Data: 
# --------------------------------------------------------

param(
    [string]$RepoUrl = "https://github.com/gabrieldonlopes/games_c.git",  # Altere para seu repositório
    [string]$ProjectDir = "$env:USERPROFILE\Documents\games_do_gabe"
)

# Configurações
$ErrorActionPreference = "Stop"
$ProgressPreference = 'SilentlyContinue'  # Acelera downloads

# URLs de download
$urls = @{
    "Git" = "https://github.com/git-for-windows/git/releases/download/v2.43.0.windows.1/Git-2.43.0-64-bit.exe"
    "CMake" = "https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1-windows-x86_64.msi"
    "GCC" = "https://github.com/niXman/mingw-builds-binaries/releases/download/13.2.0-rt_v11-rev1/x86_64-13.2.0-release-win32-seh-ucrt-rt_v11-rev1.7z"
    "SDL2" = "https://github.com/libsdl-org/SDL/releases/download/release-2.30.0/SDL2-devel-2.30.0-mingw.zip"
}

# Diretórios
$downloadDir = "$env:TEMP\setup_downloads"
$mingwDir = "C:\mingw64"

# Função para verificar se programa está no PATH
function Test-CommandExists {
    param($command)
    $null -ne (Get-Command $command -ErrorAction SilentlyContinue)
}

# Função para adicionar ao PATH do sistema
function Add-ToSystemPath {
    param($path)
    
    $oldPath = [Environment]::GetEnvironmentVariable("Path", "Machine")
    if ($oldPath -notlike "*$path*") {
        $newPath = "$oldPath;$path"
        [Environment]::SetEnvironmentVariable("Path", $newPath, "Machine")
        Write-Host "✅ Adicionado ao PATH do sistema: $path" -ForegroundColor Green
        return $true
    }
    Write-Host "ℹ️  Já está no PATH: $path" -ForegroundColor Yellow
    return $false
}

# Função para adicionar ao PATH do usuário atual
function Add-ToUserPath {
    param($path)
    
    $oldPath = [Environment]::GetEnvironmentVariable("Path", "User")
    if ($oldPath -notlike "*$path*") {
        $newPath = "$oldPath;$path"
        [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
        Write-Host "✅ Adicionado ao PATH do usuário: $path" -ForegroundColor Green
        return $true
    }
    Write-Host "ℹ️  Já está no PATH do usuário: $path" -ForegroundColor Yellow
    return $false
}

# Criar diretório de downloads
if (-not (Test-Path $downloadDir)) {
    New-Item -ItemType Directory -Path $downloadDir -Force | Out-Null
}

Write-Host "=" * 60 -ForegroundColor Cyan
Write-Host "🔍 VERIFICAÇÕES DE INSTALAÇÃO" -ForegroundColor Cyan
Write-Host "=" * 60 -ForegroundColor Cyan

# 1. Verificar Git
Write-Host "`n📌 Verificando Git..." -ForegroundColor Yellow
$gitInstalled = Test-CommandExists "git"
if (-not $gitInstalled) {
    Write-Host "❌ Git não encontrado" -ForegroundColor Red
    $downloadGit = $true
} else {
    $gitVersion = git --version
    Write-Host "✅ Git já instalado: $gitVersion" -ForegroundColor Green
    $downloadGit = $false
}

# 2. Verificar CMake
Write-Host "`n📌 Verificando CMake..." -ForegroundColor Yellow
$cmakeInstalled = Test-CommandExists "cmake"
if (-not $cmakeInstalled) {
    Write-Host "❌ CMake não encontrado" -ForegroundColor Red
    $downloadCMake = $true
} else {
    $cmakeVersion = cmake --version | Select-Object -First 1
    Write-Host "✅ CMake já instalado: $cmakeVersion" -ForegroundColor Green
    $downloadCMake = $false
}

# 3. Verificar GCC (MinGW)
Write-Host "`n📌 Verificando GCC (MinGW)..." -ForegroundColor Yellow
$gccInstalled = Test-CommandExists "gcc"
if (-not $gccInstalled) {
    Write-Host "❌ GCC não encontrado" -ForegroundColor Red
    $downloadGCC = $true
} else {
    $gccVersion = gcc --version | Select-Object -First 1
    Write-Host "✅ GCC já instalado: $gccVersion" -ForegroundColor Green
    $downloadGCC = $false
}

# 4. Verificar SDL2 (como dependência)
Write-Host "`n📌 Verificando SDL2..." -ForegroundColor Yellow
$sdl2Path = "C:\SDL2"
if (-not (Test-Path $sdl2Path)) {
    Write-Host "❌ SDL2 não encontrado" -ForegroundColor Red
    $downloadSDL2 = $true
} else {
    Write-Host "✅ SDL2 encontrado em: $sdl2Path" -ForegroundColor Green
    $downloadSDL2 = $false
}

# 5. Verificar repositório
Write-Host "`n📌 Verificando repositório do projeto..." -ForegroundColor Yellow

$cloneRepo = $false
$updateRepo = $false

if (-not (Test-Path $ProjectDir)) {
    Write-Host "ℹ️  Diretório do projeto não existe. Será clonado." -ForegroundColor Yellow
    $cloneRepo = $true
} else {
    # Verificar se é um repositório git válido
    if (Test-Path "$ProjectDir\.git") {
        Write-Host "✅ Projeto já existe em: $ProjectDir" -ForegroundColor Green
        
        # Verificar se há atualizações disponíveis
        Push-Location $ProjectDir
        
        # Buscar atualizações do repositório remoto
        Write-Host "🔍 Verificando atualizações do repositório..." -ForegroundColor Yellow
        git fetch
        
        # Verificar se o branch local está atrás do remoto
        $localCommit = git rev-parse @
        $remoteCommit = git rev-parse @{u}
        $baseCommit = git merge-base @ @{u}
        
        if ($localCommit -eq $remoteCommit) {
            Write-Host "✅ Repositório já está atualizado!" -ForegroundColor Green
            $updateRepo = $false
        } elseif ($localCommit -eq $baseCommit) {
            Write-Host "🔄 Repositório está atrás. Será atualizado (git pull)..." -ForegroundColor Yellow
            $updateRepo = $true
        } else {
            Write-Host "⚠️  Repositório tem alterações locais. Tentando atualizar..." -ForegroundColor Yellow
            $updateRepo = $true
        }
        
        Pop-Location
    } else {
        Write-Host "⚠️  Diretório existe mas não é um repositório git válido." -ForegroundColor Yellow
        Write-Host "ℹ️  Será removido e clonado novamente." -ForegroundColor Yellow
        
        # Opção: perguntar ao usuário
        $response = Read-Host "Remover diretório existente e clonar novamente? (S/N)"
        if ($response -eq 'S' -or $response -eq 's') {
            Remove-Item -Path $ProjectDir -Recurse -Force
            $cloneRepo = $true
        } else {
            Write-Host "❌ Operação cancelada pelo usuário" -ForegroundColor Red
            exit
        }
    }
}

# Resumo das verificações
Write-Host "`n" + ("=" * 60) -ForegroundColor Cyan
Write-Host "📋 RESUMO DAS VERIFICAÇÕES:" -ForegroundColor Cyan
Write-Host "=" * 60 -ForegroundColor Cyan
Write-Host "Git:     $(if($gitInstalled){'✅ Instalado'}else{'❌ Será instalado'})" -ForegroundColor $(if($gitInstalled){'Green'}else{'Red'})
Write-Host "CMake:   $(if($cmakeInstalled){'✅ Instalado'}else{'❌ Será instalado'})" -ForegroundColor $(if($cmakeInstalled){'Green'}else{'Red'})
Write-Host "GCC:     $(if($gccInstalled){'✅ Instalado'}else{'❌ Será instalado'})" -ForegroundColor $(if($gccInstalled){'Green'}else{'Red'})
Write-Host "SDL2:    $(if(-not $downloadSDL2){'✅ Encontrado'}else{'❌ Será baixado'})" -ForegroundColor $(if(-not $downloadSDL2){'Green'}else{'Red'})
Write-Host "Repositório: $(if(-not $cloneRepo){'✅ Existente'}else{'📥 Será clonado'})" -ForegroundColor $(if(-not $cloneRepo){'Green'}else{'Yellow'})

# Perguntar se quer continuar
Write-Host "`n"
$confirmation = Read-Host "Deseja continuar com as instalações? (S/N)"
if ($confirmation -ne 'S' -and $confirmation -ne 's') {
    Write-Host "❌ Operação cancelada pelo usuário" -ForegroundColor Red
    exit
}

# FUNÇÕES DE INSTALAÇÃO
function Install-Git {
    Write-Host "`n📥 Baixando Git..." -ForegroundColor Cyan
    $installer = "$downloadDir\GitInstaller.exe"
    Invoke-WebRequest -Uri $urls["Git"] -OutFile $installer
    
    Write-Host "🔧 Instalando Git (modo silencioso)..." -ForegroundColor Cyan
    Start-Process -FilePath $installer -ArgumentList "/VERYSILENT /NORESTART /SUPPRESSMSGBOXES" -Wait
    
    # Adicionar ao PATH
    $gitPath = "C:\Program Files\Git\bin"
    Add-ToSystemPath $gitPath
    Add-ToUserPath $gitPath
    
    # Atualizar PATH da sessão atual
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "✅ Git instalado com sucesso!" -ForegroundColor Green
}

function Install-CMake {
    Write-Host "`n📥 Baixando CMake..." -ForegroundColor Cyan
    $installer = "$downloadDir\CMakeInstaller.msi"
    Invoke-WebRequest -Uri $urls["CMake"] -OutFile $installer
    
    Write-Host "🔧 Instalando CMake..." -ForegroundColor Cyan
    Start-Process -FilePath "msiexec" -ArgumentList "/i `"$installer`" /quiet /norestart" -Wait
    
    # Adicionar ao PATH
    $cmakePath = "C:\Program Files\CMake\bin"
    Add-ToSystemPath $cmakePath
    Add-ToUserPath $cmakePath
    
    # Atualizar PATH da sessão atual
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "✅ CMake instalado com sucesso!" -ForegroundColor Green
}

function Install-GCC {
    Write-Host "`n📥 Baixando GCC (MinGW)..." -ForegroundColor Cyan
    $archive = "$downloadDir\mingw.7z"
    Invoke-WebRequest -Uri $urls["GCC"] -OutFile $archive
    
    Write-Host "🔧 Extraindo GCC para $mingwDir..." -ForegroundColor Cyan
    
    # Verificar se 7-Zip está instalado
    if (-not (Test-CommandExists "7z")) {
        Write-Host "⚠️  7-Zip não encontrado. Instalando..." -ForegroundColor Yellow
        $sevenZipUrl = "https://www.7-zip.org/a/7z2409-x64.exe"
        $sevenZipInstaller = "$downloadDir\7zInstaller.exe"
        Invoke-WebRequest -Uri $sevenZipUrl -OutFile $sevenZipInstaller
        Start-Process -FilePath $sevenZipInstaller -ArgumentList "/S" -Wait
        $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    }
    
    # Extrair usando 7-Zip
    & "7z" x $archive -o"C:\" -y | Out-Null
    
    # Adicionar ao PATH
    $gccPath = "$mingwDir\bin"
    Add-ToSystemPath $gccPath
    Add-ToUserPath $gccPath
    
    # Atualizar PATH da sessão atual
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    
    Write-Host "✅ GCC instalado com sucesso!" -ForegroundColor Green
}

function Install-SDL2 {
    Write-Host "`n📥 Baixando SDL2..." -ForegroundColor Cyan
    $sdl2Zip = "$downloadDir\SDL2.zip"
    Invoke-WebRequest -Uri $urls["SDL2"] -OutFile $sdl2Zip
    
    Write-Host "🔧 Extraindo SDL2 para C:\SDL2..." -ForegroundColor Cyan
    Expand-Archive -Path $sdl2Zip -DestinationPath "C:\" -Force
    Rename-Item -Path "C:\SDL2-2.30.0" -NewName "SDL2" -Force
    
    Write-Host "✅ SDL2 instalado em C:\SDL2" -ForegroundColor Green
}

function Clone-Or-Update-Repository {
    param(
        [string]$RepoUrl,
        [string]$ProjectDir
    )
    
    if ($cloneRepo) {
        Write-Host "`n📥 Clonando repositório..." -ForegroundColor Cyan
        Write-Host "Repositório: $RepoUrl" -ForegroundColor Cyan
        Write-Host "Destino: $ProjectDir" -ForegroundColor Cyan
        
        git clone $RepoUrl $ProjectDir
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "✅ Repositório clonado com sucesso!" -ForegroundColor Green
            return $true
        } else {
            Write-Host "❌ Erro ao clonar repositório" -ForegroundColor Red
            return $false
        }
    }
    elseif ($updateRepo) {
        Write-Host "`n🔄 Atualizando repositório..." -ForegroundColor Cyan
        Push-Location $ProjectDir
        
        # Salvar mudanças locais se houver (opcional)
        git stash save "Backup automático antes do pull - $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')"
        
        # Fazer pull
        git pull --rebase
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "✅ Repositório atualizado com sucesso!" -ForegroundColor Green
            
            # Restaurar mudanças locais se houver (opcional)
            git stash pop
            if ($LASTEXITCODE -ne 0) {
                Write-Host "⚠️  Conflitos detectados. Resolva manualmente." -ForegroundColor Yellow
            }
            
            Pop-Location
            return $true
        } else {
            Write-Host "❌ Erro ao atualizar repositório" -ForegroundColor Red
            Pop-Location
            return $false
        }
    }
    
    return $true
}

function Compile-Project {
    Write-Host "`n🔨 COMPILANDO PROJETO COM CMAKE" -ForegroundColor Cyan
    Write-Host "=" * 60 -ForegroundColor Cyan
    
    # Criar diretório build se não existir
    $buildDir = "$ProjectDir\build"
    if (-not (Test-Path $buildDir)) {
        New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
    }
    
    # Configurar CMake
    Write-Host "📌 Configurando CMake..." -ForegroundColor Yellow
    Push-Location $buildDir
    
    # Configurar variáveis de ambiente para SDL2 se necessário
    $env:CMAKE_PREFIX_PATH = "C:\SDL2"
    
    # Executar CMake
    cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Erro na configuração do CMake" -ForegroundColor Red
        Pop-Location
        return $false
    }
    
    # Compilar
    Write-Host "📌 Compilando projeto..." -ForegroundColor Yellow
    cmake --build . --config Release
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Erro na compilação" -ForegroundColor Red
        Pop-Location
        return $false
    }
    
    Pop-Location
    Write-Host "✅ Projeto compilado com sucesso!" -ForegroundColor Green
    return $true
}

function Find-And-Run-Executable {
    Write-Host "`n🚀 PROCURANDO EXECUTÁVEL" -ForegroundColor Cyan
    Write-Host "=" * 60 -ForegroundColor Cyan
    
    # Procurar por arquivos .exe no diretório build
    $exeFiles = Get-ChildItem -Path $ProjectDir -Filter "*.exe" -Recurse | Where-Object { $_.FullName -like "*build*" -or $_.FullName -like "*Release*" -or $_.FullName -like "*Debug*" }
    
    if ($exeFiles.Count -eq 0) {
        Write-Host "❌ Nenhum executável encontrado no projeto" -ForegroundColor Red
        return $false
    }
    
    # Pegar o primeiro executável encontrado
    $exePath = $exeFiles[0].FullName
    Write-Host "✅ Executável encontrado: $exePath" -ForegroundColor Green
    
    # Copiar SDL2.dll para o diretório do executável se necessário
    $sdl2Dll = "C:\SDL2\lib\x64\SDL2.dll"
    $exeDir = Split-Path $exePath
    if (Test-Path $sdl2Dll) {
        Copy-Item $sdl2Dll $exeDir -Force
        Write-Host "📋 SDL2.dll copiada para o diretório do executável" -ForegroundColor Yellow
    }
    
    # Executar
    Write-Host "`n🎮 Executando aplicação..." -ForegroundColor Green
    Write-Host "-" * 40 -ForegroundColor Green
    Start-Process -FilePath $exePath -WorkingDirectory $exeDir -Wait
    
    return $true
}

# EXECUÇÃO PRINCIPAL DAS INSTALAÇÕES
Write-Host "`n" + ("=" * 60) -ForegroundColor Green
Write-Host "🚀 INICIANDO INSTALAÇÕES" -ForegroundColor Green
Write-Host "=" * 60 -ForegroundColor Green

# Instalar Git se necessário
if ($downloadGit) { Install-Git }

# Instalar CMake se necessário
if ($downloadCMake) { Install-CMake }

# Instalar GCC se necessário
if ($downloadGCC) { Install-GCC }

# Baixar SDL2 se necessário
if ($downloadSDL2) { Install-SDL2 }

# Clonar repositório se necessário
if ($cloneRepo) {
    if (-not (Clone-Repository)) {
        Write-Host "❌ Falha ao clonar repositório. Abortando." -ForegroundColor Red
        exit 1
    }
}

# Compilar projeto
if (Compile-Project) {
    # Abrir executável
    Find-And-Run-Executable
} else {
    Write-Host "❌ Falha na compilação do projeto" -ForegroundColor Red
    exit 1
}

Write-Host "`n" + ("=" * 60) -ForegroundColor Green
Write-Host "✅ PROCESSO CONCLUÍDO COM SUCESSO!" -ForegroundColor Green
Write-Host "=" * 60 -ForegroundColor Green