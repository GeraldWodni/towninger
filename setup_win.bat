:: Set directories and URLs
set GBDK_URL=https://github.com/gbdk-2020/gbdk-2020/releases/download/4.3.0/gbdk-win64.zip
set BGB_URL=https://bgb.bircd.org/bgbw64.zip

:: Check for GBDK directory
if not exist gbdk (
    echo Downloading GBDK...
    curl -L -o gbdk.zip "%GBDK_URL%"
    echo Extracting GBDK...
    powershell -Command "Expand-Archive -Path 'gbdk.zip' -DestinationPath '.'"
    del gbdk.zip
    echo GBDK setup complete.
) else (
    echo GBDK already exists.
)

:: Check for BGB directory
if not exist "bgb" (
    echo Downloading BGB...
    curl -L -o bgb.zip "%BGB_URL%"
    echo Extracting BGB...
    powershell -Command "Expand-Archive -Path 'bgb.zip' -DestinationPath 'bgb'"
    del bgb.zip
    echo BGB setup complete.
) else (
    echo BGB already exists.
)