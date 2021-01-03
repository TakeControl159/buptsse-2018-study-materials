<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Juicers and Their Cost</TITLE>
            </HEAD>
            <BODY>
                <xsl:variable name="priceAdjuster" select="document('file://localhost/xml-course/xsl/labs/lab03/answer/priceAdjuster2.xml')"/>
                <xsl:if test="$priceAdjuster/priceAdjustment/adjustment/@action='no change'">
                    <xsl:call-template name="createJuicerCostTable"/>
                </xsl:if>
                <xsl:if test="$priceAdjuster/priceAdjustment/adjustment/@action='increase'">
                    <xsl:variable name="sizeIncrease" select="$priceAdjuster/priceAdjustment/adjustment/sizeIncrease"/>
                    <xsl:call-template name="createJuicerCostTable">
                        <xsl:with-param name="sizeIncrease" select="$sizeIncrease"/>
                    </xsl:call-template>
                </xsl:if>
            </BODY>
        </HTML>
    </xsl:template>

    <xsl:template name="createJuicerCostTable">
        <xsl:param name="sizeIncrease" select="0"/>
        <TABLE BORDER="1" WIDTH="50%">
            <TR>
                <TH>Juicer</TH><TH>Cost</TH>
            </TR>
            <xsl:for-each select="/juicers/juicer">
                <TR>
                    <TD><xsl:value-of select="name"/></TD>
                    <xsl:variable name="newCost" select="((cost[@currency='USD'] * ($sizeIncrease div 100)) + cost[@currency='USD'])"/>
                    <TD><xsl:value-of select="format-number($newCost, '$#.00')"/></TD>
                </TR>
            </xsl:for-each>
        </TABLE>
    </xsl:template>

</xsl:stylesheet>