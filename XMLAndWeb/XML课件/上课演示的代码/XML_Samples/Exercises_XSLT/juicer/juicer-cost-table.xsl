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
                <xsl:variable name="priceAdjuster" select="document('priceAdjuster2.xml')"/>
                <xsl:if test="$priceAdjuster/priceAdjustment/adjustment/@action='no change'">
                    <TABLE BORDER="1" WIDTH="50%">
                        <TR>
                            <TH>Juicer</TH><TH>Cost</TH>
                        </TR>
                        <xsl:for-each select="/juicers/juicer">
                            <TR>
                                <TD><xsl:value-of select="name"/></TD>
                                <TD><xsl:value-of select="format-number(cost[@currency='USD'], '$#.00')"/></TD>
                            </TR>
                        </xsl:for-each>
                    </TABLE>
                </xsl:if>
                <xsl:if test="$priceAdjuster/priceAdjustment/adjustment/@action='increase'">
                    <xsl:variable name="sizeIncrease" select="$priceAdjuster/priceAdjustment/adjustment/sizeIncrease"/>
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
                </xsl:if>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>