# How to install Root
Download the root file https://root.cern/install/all_releases/ 

The binary root file is recommended for the local computer because it doesn't need to construct the specific environment in your local computer.

Then, you need to source the root in the terminal to use it in the terminal.
```shell
$ source pathname/root/bin/thisroot.sh
```
After the command, the root could be used in the terminal.

For the convenience, it is helpful to add a command in the .bash file.

In the linux OS,
```shell
$ vim .bash
```
In the mac OS,
```shell
$ vim .zshrc
```
Then add source pathname/root/bin/thisroot.sh in the bash file.
# How to install tenserflow
In the icepp environment.
```shell
$ python3 -m v env
$ source env/bin/activate
$ pip install --upgrade pip
$ pip install tensorflow
```

# How to install pytorch
In the icepp environment.
```shell
$ python3 -m v env
$ source env/bin/activate
$ pip install --upgrade pip
$ pip3 install torch==1.11.0+cu113 torchvision==0.12.0+cu113 torchaudio==0.11.0+cu113 -f https://download.pytorch.org/whl/cu113/torch_stable.html
$ pip install torch-scatter torch-sparse torch-cluster torch-spline-conv torch-geometric -f https://data.pyg.org/whl/torch-1.10.0+cu113.html

```
