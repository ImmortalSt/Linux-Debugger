
enum x64userStructOffsets {
    _r15           = 0x00000000,      
    _r14           = 0x00000008,      
    _r13           = 0x00000010,      
    _r12           = 0x00000018,      
    _rbp           = 0x00000020,      
    _rbx           = 0x00000028,      
    _r11           = 0x00000030,      
    _r10           = 0x00000038,      
    _r9            = 0x00000040,      
    _r8            = 0x00000048,      
    _rax           = 0x00000050,      
    _rcx           = 0x00000058,      
    _rdx           = 0x00000060,      
    _rsi           = 0x00000068,      
    _rdi           = 0x00000070,      
    orig_rax       = 0x00000078,      
    _rip           = 0x00000080,      
    _cs            = 0x00000088,      
    eflags         = 0x00000090,      
    _rsp           = 0x00000098,      
    _ss            = 0x000000A0,      
    fs_base        = 0x000000A8,      
    gs_base        = 0x000000B0,      
    _ds            = 0x000000B8,      
    _es            = 0x000000C0,      
    _fs            = 0x000000C8,      
    _gs            = 0x000000D0,
    u_fpvalid      = 0x000000D8,
    cwd            = 0x00000000 + 0x000000E0,   
    swd            = 0x00000002 + 0x000000E0,   
    ftw            = 0x00000004 + 0x000000E0,   
    fop            = 0x00000006 + 0x000000E0,   
    _rip_i387      = 0x00000008 + 0x000000E0,   
    rdp            = 0x00000010 + 0x000000E0,   
    _mxcsr         = 0x00000018 + 0x000000E0,   
    mxcr_mask      = 0x0000001C + 0x000000E0,   
    st_space       = 0x00000020 + 0x000000E0,   
    xmm_space      = 0x000000A0 + 0x000000E0,   
    u_tsize        = 0x000002E0,
    u_dsize        = 0x000002E8,
    u_ssize        = 0x000002F0,
    start_code     = 0x000002F8,
    start_stack    = 0x00000300,
    _signal         = 0x00000308,
    reserved       = 0x00000310,
    anonymous_0    = 0x00000318,
    anonymous_1    = 0x00000320,
    magic          = 0x00000328,
    u_comm         = 0x00000330,
    u_debugreg     = 0x00000350
};












