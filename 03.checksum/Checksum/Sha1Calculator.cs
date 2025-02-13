using System.Security.Cryptography;

namespace _03.checksum.Checksum;

public class Sha1Calculator : ChecksumCalculatorBase
{
    protected override HashAlgorithm GetHashAlgorithm()
    {
        return SHA1.Create();
    }
}