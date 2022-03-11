# How to install Root
Download the root file https://root.cern/install/all_releases/ 

The binary root file is recommended for the local computer because it doesn't need to construct the specific environment in your local computer.

Then, you need to source the root in the terminal to use it in the terminal.
```shell
$ source pathname/root/bin/thisroot.sh
```
Therefore, the root could be used in the terminal.

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
```shell
$ pip install graph_nets "tensorflow>=1.15,<2" "dm-sonnet<2" "tensorflow_probability<0.9"
```

# How to install pytorch
