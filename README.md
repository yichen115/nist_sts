# nist_sts
较原项目将产生随机数序列部分删除，改为从文件中读取随机数序列进行测试

```
./build_linux.sh
cd build/test
./nist_sts_test ../../test.bin
```

本项目中大部分代码搬运自[https://github.com/kravietz/nist-sts](https://github.com/kravietz/nist-sts "")，对其作了一些修改，使其适合作为一个库使用。  

另外，增加了自相关测试、扑克测试、游程分布测试三项原项目中没有，但是国密《GM/T 0005-2012 随机性检测规范》中要求有的测试。