; ModuleID = 'C:/Users/j54mao/ECE423/ECE-423-Labs/HLS/ECE423_Lab2/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: noinline
define void @apatb_idct_ir([8 x i16]* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="8" %DCAC, [8 x i8]* noalias nocapture nonnull "fpga.decayed.dim.hint"="8" %blockout) local_unnamed_addr #0 {
entry:
  %DCAC_copy = alloca [8 x [8 x i16]], align 512
  %blockout_copy = alloca [8 x [8 x i8]], align 512
  %0 = bitcast [8 x i16]* %DCAC to [8 x [8 x i16]]*
  %1 = bitcast [8 x i8]* %blockout to [8 x [8 x i8]]*
  call fastcc void @copy_in([8 x [8 x i16]]* nonnull %0, [8 x [8 x i16]]* nonnull align 512 %DCAC_copy, [8 x [8 x i8]]* nonnull %1, [8 x [8 x i8]]* nonnull align 512 %blockout_copy)
  %2 = getelementptr inbounds [8 x [8 x i16]], [8 x [8 x i16]]* %DCAC_copy, i32 0, i32 0
  %3 = getelementptr inbounds [8 x [8 x i8]], [8 x [8 x i8]]* %blockout_copy, i32 0, i32 0
  call void @apatb_idct_hw([8 x i16]* %2, [8 x i8]* %3)
  call void @copy_back([8 x [8 x i16]]* %0, [8 x [8 x i16]]* %DCAC_copy, [8 x [8 x i8]]* %1, [8 x [8 x i8]]* %blockout_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([8 x [8 x i16]]* noalias readonly, [8 x [8 x i16]]* noalias align 512, [8 x [8 x i8]]* noalias readonly, [8 x [8 x i8]]* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a8a8i16([8 x [8 x i16]]* align 512 %1, [8 x [8 x i16]]* %0)
  call fastcc void @onebyonecpy_hls.p0a8a8i8([8 x [8 x i8]]* align 512 %3, [8 x [8 x i8]]* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a8a8i16([8 x [8 x i16]]* noalias align 512, [8 x [8 x i16]]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [8 x [8 x i16]]* %0, null
  %3 = icmp eq [8 x [8 x i16]]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop.split, %copy
  %for.loop.idx10 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop.split ]
  br label %for.loop2

for.loop2:                                        ; preds = %for.loop2, %for.loop
  %for.loop.idx39 = phi i64 [ 0, %for.loop ], [ %for.loop.idx3.next, %for.loop2 ]
  %dst.addr57 = getelementptr [8 x [8 x i16]], [8 x [8 x i16]]* %0, i64 0, i64 %for.loop.idx10, i64 %for.loop.idx39
  %src.addr68 = getelementptr [8 x [8 x i16]], [8 x [8 x i16]]* %1, i64 0, i64 %for.loop.idx10, i64 %for.loop.idx39
  %5 = load i16, i16* %src.addr68, align 2
  store i16 %5, i16* %dst.addr57, align 2
  %for.loop.idx3.next = add nuw nsw i64 %for.loop.idx39, 1
  %exitcond = icmp ne i64 %for.loop.idx3.next, 8
  br i1 %exitcond, label %for.loop2, label %for.loop.split

for.loop.split:                                   ; preds = %for.loop2
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx10, 1
  %exitcond11 = icmp ne i64 %for.loop.idx.next, 8
  br i1 %exitcond11, label %for.loop, label %ret

ret:                                              ; preds = %for.loop.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a8a8i8([8 x [8 x i8]]* noalias align 512, [8 x [8 x i8]]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [8 x [8 x i8]]* %0, null
  %3 = icmp eq [8 x [8 x i8]]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop.split, %copy
  %for.loop.idx10 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop.split ]
  br label %for.loop2

for.loop2:                                        ; preds = %for.loop2, %for.loop
  %for.loop.idx39 = phi i64 [ 0, %for.loop ], [ %for.loop.idx3.next, %for.loop2 ]
  %dst.addr57 = getelementptr [8 x [8 x i8]], [8 x [8 x i8]]* %0, i64 0, i64 %for.loop.idx10, i64 %for.loop.idx39
  %src.addr68 = getelementptr [8 x [8 x i8]], [8 x [8 x i8]]* %1, i64 0, i64 %for.loop.idx10, i64 %for.loop.idx39
  %5 = load i8, i8* %src.addr68, align 1
  store i8 %5, i8* %dst.addr57, align 1
  %for.loop.idx3.next = add nuw nsw i64 %for.loop.idx39, 1
  %exitcond = icmp ne i64 %for.loop.idx3.next, 8
  br i1 %exitcond, label %for.loop2, label %for.loop.split

for.loop.split:                                   ; preds = %for.loop2
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx10, 1
  %exitcond11 = icmp ne i64 %for.loop.idx.next, 8
  br i1 %exitcond11, label %for.loop, label %ret

ret:                                              ; preds = %for.loop.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([8 x [8 x i16]]* noalias, [8 x [8 x i16]]* noalias readonly align 512, [8 x [8 x i8]]* noalias, [8 x [8 x i8]]* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a8a8i16([8 x [8 x i16]]* %0, [8 x [8 x i16]]* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0a8a8i8([8 x [8 x i8]]* %2, [8 x [8 x i8]]* align 512 %3)
  ret void
}

declare void @apatb_idct_hw([8 x i16]*, [8 x i8]*)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([8 x [8 x i16]]* noalias, [8 x [8 x i16]]* noalias readonly align 512, [8 x [8 x i8]]* noalias, [8 x [8 x i8]]* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a8a8i8([8 x [8 x i8]]* %2, [8 x [8 x i8]]* align 512 %3)
  ret void
}

define void @idct_hw_stub_wrapper([8 x i16]*, [8 x i8]*) #4 {
entry:
  %2 = bitcast [8 x i16]* %0 to [8 x [8 x i16]]*
  %3 = bitcast [8 x i8]* %1 to [8 x [8 x i8]]*
  call void @copy_out([8 x [8 x i16]]* null, [8 x [8 x i16]]* %2, [8 x [8 x i8]]* null, [8 x [8 x i8]]* %3)
  %4 = bitcast [8 x [8 x i16]]* %2 to [8 x i16]*
  %5 = bitcast [8 x [8 x i8]]* %3 to [8 x i8]*
  call void @idct_hw_stub([8 x i16]* %4, [8 x i8]* %5)
  call void @copy_in([8 x [8 x i16]]* null, [8 x [8 x i16]]* %2, [8 x [8 x i8]]* null, [8 x [8 x i8]]* %3)
  ret void
}

declare void @idct_hw_stub([8 x i16]*, [8 x i8]*)

attributes #0 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
