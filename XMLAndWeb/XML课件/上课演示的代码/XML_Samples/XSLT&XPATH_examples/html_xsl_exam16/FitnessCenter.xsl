<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Fitness Center</TITLE>
            </HEAD>
            <BODY>
                Membership Fee Revenue:
                <xsl:value-of select="sum(FitnessCenter/Member/MembershipFee)"/>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>