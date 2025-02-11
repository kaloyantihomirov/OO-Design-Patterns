namespace _03.checksum.FileSystem;

public class DirectoryBuildingClient
{
    public static DirectoryEntry BuildDirectoryTree(string rootPath)
    {
        if (!Directory.Exists(rootPath))
        {
            throw new InvalidOperationException("Given path is not a path to a directory!");
        }

        var builder = new DirectoryBuilderNoSymLink();

        builder.StartDirectory(rootPath);

        AddContentsRecursively(builder, rootPath);

        builder.EndDirectory();

        return builder.GetResult();
    }

    private static void AddContentsRecursively(IAbstractDirectoryBuilder builder, string currPath)
    {
        foreach (var file in Directory.GetFiles(currPath))
        {
            long size = new FileInfo(file).Length;
            builder.AddFileEntry(file, size);
        }

        foreach (var subdirectory in Directory.GetDirectories(currPath))
        {
            builder.StartDirectory(subdirectory);
            AddContentsRecursively(builder, subdirectory);
            builder.EndDirectory();
        }
    }
}