# makefile for System: GO_BACK_N

sctAUTOCFGDEP =
sctCOMPFLAGS = -DXUSE_GENERIC_FUNC

!include $(SCTDIR)\make.opt

default: GO_BACK_N$(sctEXTENSION)

GO_BACK_N$(sctEXTENSION): \
  GO_BACK_N$(sctOEXTENSION) \
  $(sctLINKKERNELDEP)
	$(sctLD) @<<
	$(sctLDFLAGS)
	 GO_BACK_N$(sctOEXTENSION) $(sctLINKKERNEL)
	/OUT:GO_BACK_N$(sctEXTENSION)
<<

GO_BACK_N$(sctOEXTENSION): \
  GO_BACK_N.c
	$(sctCC) @<<
	$(sctCPPFLAGS) $(sctCCFLAGS)
	$(sctIFDEF)
	/FoGO_BACK_N$(sctOEXTENSION)
	GO_BACK_N.c
<<
