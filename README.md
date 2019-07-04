# ScriptShield
ScriptShield is a backwards compatible application execution framework that automatically ensures the
confdentiality and integrity of scripts by executing scripting
language interpreters inside SGX enclaves. We have implemented
a prototype of our framework and tested with Lua, JavaScript and
Squirrel. Our experimental results show that ScriptShield does not
introduce noticeable overhead. We also demonstrate the benefts of
running interpreters inside SGX, such as only signing the trusted
enclave once while allowing execution of arbitrary scripts and
transparent protection of the confdentiality and integrity of scripts.
## Requirements
SGX needs following hardware requirements to run SGX:

- CPU with Intel SGX support (6th Generation Intel Core Processor or newer, you can check in the list of SGX supported hardware)
- Intel SGX option enabled in BIOS

Also, ensure that you have one of the follwing operating systems required by SGX:

- Ubuntu 16.04 LTS 64-bit Desktop version
- Ubuntu 16.04 LTS 64-bit Server version
- Red Hat Enterprise Linux Server release 7.4 64bits
- CentOS 7.4.1708 64bits
- SUSE Linux Enterprise Server 12 64bits
Please refer to the Intel SGX for Linux project for the cutting edge version.
### Installing SGX
- Download them from https://download.01.org/intel-sgx/linux-2.4/. Then, follow these instructions to install.
- Install dependencies for Instal SGX PSW and SGX SDK first. Following instructions are for Ubuntu 16.04, you can find detailed guilde from the [Intel SGX Installation Guide](https://download.01.org/intel-sgx/linux-2.4/docs/Intel_SGX_Installation_Guide_Linux_2.4_Open_Source.pdf)

## Compiling
- Compiling musl libc. musl libc is under src/musl-sgx. Following the instruction to compile musl libc first before compiling sample. 
- In each Sample, just run make command which will compile the dependencies for each interpreter and sgx program.
- For each interpreter, the dependent libs are listed under libs. 
## Running
- Simply run the program with input ad the script you are going to run.
