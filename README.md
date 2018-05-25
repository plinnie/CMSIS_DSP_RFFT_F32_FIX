# CMSIS_DSP_RFFT_F32_FIX
Some code to enable in-place F32 RFFT for ARM CMSIS DSP library.

Normally the ARM CMSIS library will only allow out-of-place Real FFT operations, which takes up twice the required amount of RAM. This code executes the Real FFT in-place, saving you valueble RAM

As an add-on it also has some RFFT F32 constant instances, for older version of ARM CMSIS DSP. More recent versions of ARM DSP already have these constant instances.

Note that this code requires the ARM CMSIS DSP library. Tested for 4.5.
