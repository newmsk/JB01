# JB01

## Description
#### JB01 LZSS compression library python bindings, all version source code could be downloaded here:
https://www.autoitscript.com/cgi-bin/countdown.pl?code/LZSS.zip
#### Porting latest `v1_40a` version compression algo

## Install
```shell
pip install jb01
```

## Usage
```python
import jb01
c = jb01.compress(b'test', level=4)
print(c)
d = jb01.decompress(c)
print(d)
```

## Credits
* [Jonathan Bennett](https://www.autoitscript.com/)
* [pybind11](https://github.com/pybind/pybind11)

