<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Platinum Members</TITLE>
            </HEAD>
            <BODY>
                <H1>Fitness Center Platinum Members (sorted alphabetically)</H1>
                <UL>
                   <xsl:for-each select="/FitnessCenter/Member[@level='platinum']">
                       <xsl:sort select="Name" order="ascending"/>
                       <LI><xsl:value-of select="Name"/></LI>
                   </xsl:for-each>
                </UL>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>