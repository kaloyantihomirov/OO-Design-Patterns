namespace _03.checksum.FileSystem;

public static class ShortcutHelper
{
    //SOURCE: https://stackoverflow.com/questions/310222/getting-target-of-windows-shortcut-lnk-file
    public static string GetLnkTarget(string lnkPath)
    {
        string fullPath= System.IO.Path.GetFullPath(lnkPath);
        var shl = new Shell32.Shell();
        var dir = shl.NameSpace(System.IO.Path.GetDirectoryName(fullPath));
        var itm = dir.Items().Item(System.IO.Path.GetFileName(fullPath));
        var lnk = (Shell32.ShellLinkObject)itm.GetLink;
        return lnk.Path;
    }

}