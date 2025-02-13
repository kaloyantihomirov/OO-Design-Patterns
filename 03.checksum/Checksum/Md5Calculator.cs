using System.Security.Cryptography;

namespace _03.checksum.Checksum;

public class Md5Calculator : ChecksumCalculatorBase
{
    protected override HashAlgorithm GetHashAlgorithm()
    {
        return MD5.Create();
    }
}