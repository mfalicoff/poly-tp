# LOG8430_TP3

## Running the benchmarks

To run the benchmarks, you need to have the following tools installed:
- VirtualBox
- Vagrant
- Ansible

After installing the tools, you can run the following commands to start the VM and run the benchmarks:

```bash
vagrant up
```

To rerun the playbook, you can run the following command:

```bash
vagrant up --provision
```
To Destroy the VM, you can run the following command:

```bash
vagrant destroy
```

To connect to the VM, you can run the following command:

```bash
vagrant ssh
```

If you want to run everything with a single command, install make and run the following command:

```bash
make benchmark
```

If on windows, run the powershell script

```ps1
benchmark.ps1
```

## Results
You will now have the raw results in the `results` directory. you will need to have python installed to sanitize the results.
In the results directory, run the sanitize script to get the results in a csv file, you will need ton install:
- python
- numpy
- scipy

```bash
python sanitize.py
```
