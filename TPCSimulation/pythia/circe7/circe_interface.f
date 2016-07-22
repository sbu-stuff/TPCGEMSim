C...Initialize Circe
      SUBROUTINE ICIRCE(ECM,CHACC)
      IMPLICIT NONE
      DOUBLE PRECISION ECM, XMIN
      INTEGER IACC, IVER, IREV, ICHAT
C...Definition of accelerators from circe code
      integer SBAND, TESLA, XBAND
      parameter (SBAND  =  1, TESLA  =  2, XBAND  =  3)
      CHARACTER*(*) CHACC
C...Nonzero x_min value as safety measure; so long as it is reasonably
C...small it should not matter, but if made large then event rates
C...should be multiplied by a reduction factor to allow for the
C...not simulated part of the beams.
      XMIN=0D0
      IF(CHACC.EQ.'SBAND') THEN
        IACC=SBAND
      ELSE IF(CHACC.EQ.'TESLA') THEN
        IACC=TESLA
      ELSE IF(CHACC.EQ.'XBAND') THEN
        IACC=XBAND
      ELSE IF(CHACC.EQ.'JLCNLC') THEN
        IACC=XBAND
      ELSE IF(CHACC.EQ.'NLC') THEN
        IACC=XBAND
      ELSE
        PRINT*,' Accelerator ', CHACC, ' not defined! '
        PRINT*,' allowed are SBAND, TESLA, XBAND '
        PRINT*,' now using TESLA ...'
        IACC=TESLA
      ENDIF
      IVER=7
      IREV=20000501
      ICHAT=1
      CALL CIRCES(XMIN,XMIN,ECM,IACC,IVER,IREV,ICHAT)
      RETURN
      END

C...Generate beam strahlung of one event
      SUBROUTINE GCIRCE(DX1,DX2,CHPRO)
      IMPLICIT NONE
      CHARACTER*2 CHPRO
      DOUBLE PRECISION DX1, DX2
      EXTERNAL RNG
      IF(CHPRO.EQ.'EE') THEN
         CALL GIRCEE(DX1,DX2,RNG)
      ELSE IF(CHPRO.EQ.'EG') THEN
         CALL GIRCEG(DX1,DX2,RNG)
      ELSE IF(CHPRO.EQ.'GG') THEN
         CALL GIRCGG(DX1,DX2,RNG)
      ENDIF
      RETURN
      END

C...Interface to PYTHIA random number generator
      SUBROUTINE RNG(DR)
      IMPLICIT NONE
      DOUBLE PRECISION DR, PYR
      EXTERNAL PYR
      DR=PYR(0)
      RETURN
      END 

