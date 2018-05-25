# CMSIS_DSP_RFFT_F32_FIX
Some code to enable an in-place 32 bit float Real FFT for ARM CMSIS DSP library.

Normally the ARM CMSIS library will only allow out-of-place Real FFT operations, which takes up twice the required amount of RAM.  
This code executes the Real FFT in-place, saving you 50% of the required RAM.

As an add-on it also has some RFFT F32 constant instances, for older version of ARM CMSIS DSP. More recent versions of ARM DSP already have these constant instances.

Note that this code requires the ARM CMSIS DSP library. Tested for 4.5, but will probably work in 4.x and 5.x versions.

The code is a bit of a hack, but I have verified the validity for all transform sizes.
