# lucicOS

lucicOS is an educational, UNIX-like operating system built from scratch using
the following resources:
  * [OSdev](https://wiki.osdev.org/Expanded_Main_Page)
  * [Little OS Book](https://littleosbook.github.io/)
  * [JamesM kernel development tutorial](http://www.jamesmolloy.co.uk/tutorial_html/)
  * [OS from 0 to 1](https://github.com/tuhdo/os01)

It can be built using the following command: `./build.sh`. To run the OS in
bochs, just run `./bochs.sh`, the same applies to qemu, just run `./qemu.sh`.

At this moment there is still a lot of work to do in order to call this a real
Operating System. It has some modules for writing to VGA, for writing to
a serial port and it has support for entering in protected mode.

The only supported architecture is x86 because it has the richest documentation
and all the tutorials on the internet are x86 oriented.

I am still struggling to find an optimal project structure that can help me
build this project faster and easier, currently I am trying different
structures found on the internet or designed by myself.
