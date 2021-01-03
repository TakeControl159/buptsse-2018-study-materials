# makefile for System: GoBackN

sctAUTOCFGDEP =
sctCOMPFLAGS = -DXUSE_GENERIC_FUNC

!include $(SCTDIR)\make.opt

default: GoBackN$(sctEXTENSION)

GoBackN$(sctEXTENSION): \
  GoBackN$(sctOEXTENSION) \
  $(sctLINKKERNELDEP)
	$(sctLD) @<<
	$(sctLDFLAGS)
	 GoBackN$(sctOEXTENSION) $(sctLINKKERNEL)
	/OUT:GoBackN$(sctEXTENSION)
<<

GoBackN$(sctOEXTENSION): \
  GoBackN.c
	$(sctCC) @<<
	$(sctCPPFLAGS) $(sctCCFLAGS)
	$(sctIFDEF)
	/FoGoBackN$(sctOEXTENSION)
	GoBackN.c
<<
