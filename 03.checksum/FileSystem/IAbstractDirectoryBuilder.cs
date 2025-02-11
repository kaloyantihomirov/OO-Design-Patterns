namespace _03.checksum.FileSystem;

public interface IAbstractDirectoryBuilder
{
    public void StartDirectory(string directoryPath);

    public void AddFileEntry(string filePath, long fileSize);

    public void EndDirectory();

    DirectoryEntry GetResult();
}