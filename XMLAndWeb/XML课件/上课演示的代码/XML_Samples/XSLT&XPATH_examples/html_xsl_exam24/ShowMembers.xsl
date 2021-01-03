<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Members</TITLE>
            </HEAD>
            <BODY>
                <H1>Fitness Center Members (sorted alphabetically)</H1>
                <UL>
                   <xsl:for-each select="/FitnessCenter/Member">
                       <xsl:sort select="Name" order="ascending"/>
                       <LI><xsl:value-of select="Name"/></LI>
                   </xsl:for-each>
                </UL>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>