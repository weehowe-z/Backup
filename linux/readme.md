## Memory management homework

- Write a module that is called mtest

- When module loaded, module will create a proc fs entry /proc/mtest

- /proc/mtest will accept 3 kind of input

 + “listvma” will print all vma of current process in the format of
   ```
    start-addr end-addr permission
    0x10000    0x20000  rwx
    0x30000    0x40000  r—
   ```

 + “findpage addr” will find va->pa translation of address in current process’s mm context and print it. If there is not va->pa translation, prink “tranlsation not found”

 + “writeval addr val” will change an unsigned long size content in current process’s virtual address into val. Note module should write to identity mapping address of addr and verify it from userspace address addr.

- All the print can be done with printk and check result with dmesg.
