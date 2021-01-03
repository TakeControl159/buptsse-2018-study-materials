<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="text"/>
    <xsl:variable name="lineSeparator" select="'-------------------------------------------'"/>

    <xsl:template match="/">
        <xsl:for-each select="/juicers/juicer">
           <xsl:value-of select="name"/>
           <xsl:text>/</xsl:text>
           <xsl:value-of select="image"/>
           <xsl:text>/</xsl:text>
           <xsl:value-of select="warranty"/>
           <xsl:text>/</xsl:text>
           <xsl:value-of select="weight"/>
           <xsl:text>/</xsl:text>
           <xsl:value-of select="cost[@currency='USD']"/>
           <xsl:text>/</xsl:text>
           <xsl:value-of select="retailer"/>
           <xsl:text>
</xsl:text>
           <xsl:value-of select="$lineSeparator"/>
           <xsl:text>
</xsl:text>
        </xsl:for-each>
    </xsl:template>

</xsl:stylesheet>