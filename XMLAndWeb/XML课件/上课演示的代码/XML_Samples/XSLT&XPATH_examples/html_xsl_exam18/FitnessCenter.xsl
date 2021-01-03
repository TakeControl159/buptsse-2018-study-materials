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
                Number of members = 
                   <xsl:value-of select="count(FitnessCenter/Member)"/>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>