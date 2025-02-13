namespace _03.checksum.FileSystem;

public abstract class FileSystemEntry 
{
    public virtual void Add(FileSystemEntry fse)
    {
        throw new NotSupportedException();
    }

    public virtual void Remove(FileSystemEntry fse)
    {
        throw new NotSupportedException();
    }

    public virtual FileSystemEntry GetChild(int i)
    {
        throw new NotSupportedException();
    }

    public virtual string GetPath()
    {
        throw new NotSupportedException();
    }

    public virtual long GetSizeInBytes()
    {
        throw new NotSupportedException();
    }

    public virtual void Print()
    {
        throw new NotSupportedException();
    }

    public virtual void Accept(IVisitor visitor)
    {
        throw new NotSupportedException();
    }
}