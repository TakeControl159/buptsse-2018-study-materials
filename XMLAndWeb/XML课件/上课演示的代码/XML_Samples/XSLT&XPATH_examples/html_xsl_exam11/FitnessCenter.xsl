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
                <xsl:for-each select="/FitnessCenter/Member">
                    <xsl:value-of select="concat('Welcome ', Name, '!')"/>
                    <BR/>
                </xsl:for-each>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>