#include <windows.h>
#include <filesystem>

namespace fs = std::filesystem;

void deleteEmptyDirectories(const fs::path& directoryPath)
{
    for (const auto& entry : fs::recursive_directory_iterator(directoryPath))
    {
        if (entry.is_directory())
        {
            if (fs::is_empty(entry.path()))
            {
                fs::remove_all(entry.path());
            }
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TCHAR szPath[MAX_PATH]; // Getting current directory exe is stored in
    GetModuleFileName(NULL, szPath, MAX_PATH);
    fs::path executablePath(szPath);
    fs::path directoryPath = executablePath.parent_path(); 

    while (true)
    {
        bool emptyDirectoryFound = false;

        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) // Iterates over all empty folders
        {
            if (entry.is_directory())
            {
                if (fs::is_empty(entry.path())) 
                {
                    fs::remove_all(entry.path());
                    emptyDirectoryFound = true;
                    break; // Break the loop and start again from the top
                }
            }
        }

        if (!emptyDirectoryFound)
        {
            break; // No more empty directories found, exit the loop
        }
    }

    return 0;
}
