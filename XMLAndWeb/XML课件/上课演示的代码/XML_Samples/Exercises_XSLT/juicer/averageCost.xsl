<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Juicers</TITLE>
            </HEAD>
            <BODY>
                Total number of juicers = 
                  <xsl:variable name="numJuicers" select="count(/juicers/juicer)"/>
                  <xsl:value-of select="$numJuicers"/>
                <BR/>
                Cost of all juicers = 
                  <xsl:variable name="totalCost" select="sum(/juicers/juicer/cost)"/>
                  <xsl:value-of select="$totalCost"/>
                <BR/>
                The average cost of the juicers =
                  <xsl:variable name="avgCost" select="$totalCost div $numJuicers"/>
                  <xsl:value-of select="format-number($avgCost, '$#.00')"/>                  
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>