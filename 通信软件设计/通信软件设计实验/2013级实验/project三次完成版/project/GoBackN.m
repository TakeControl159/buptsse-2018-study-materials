# makefile for System: GoBackN

sctAUTOCFGDEP =
sctCOMPFLAGS = -DXUSE_GENERIC_FUNC

!include $(SCTDIR)\make.opt

default: p1$(sctEXTENSION)

p1$(sctEXTENSION): \
  GoBackN$(sctOEXTENSION) \
  $(sctLINKKERNELDEP)
	$(sctLD) @<<
	$(sctLDFLAGS)
	 GoBackN$(sctOEXTENSION) $(sctLINKKERNEL)
	/OUT:p1$(sctEXTENSION)
<<

GoBackN$(sctOEXTENSION): \
  GoBackN.c
	$(sctCC) @<<
	$(sctCPPFLAGS) $(sctCCFLAGS)
	$(sctIFDEF)
	/FoGoBackN$(sctOEXTENSION)
	GoBackN.c
<<
