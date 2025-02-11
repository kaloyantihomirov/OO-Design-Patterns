    namespace _03.checksum.FileSystem;

    public class FileEntry : FileSystemEntry
    {
        private string path;
        private long sizeInBytes;

        public FileEntry(string path, long sizeInBytes)
        {
            this.path = path;
            this.sizeInBytes = sizeInBytes;
        }

        public override string GetPath()
        {
            return path;
        }

        public override long GetSizeInBytes()
        {
            return sizeInBytes;
        }

        public override void Print()
        {
            Console.WriteLine($"{path} ({sizeInBytes} bytes)");
        }

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitFile(this);
        }
    }