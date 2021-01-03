<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Determine if the Juicer XML document contains certain juicers</TITLE>
            </HEAD>
            <BODY>
                <xsl:variable name="juicerList">
                    <xsl:for-each select="/juicers/juicer[position() &lt; last()]">
                        <xsl:value-of select="name"/>
                        <xsl:text>~</xsl:text>
                    </xsl:for-each>
                    <xsl:value-of select="/juicers/juicer[last()]/name"/>
                </xsl:variable>
                Juicer List: <xsl:value-of select="$juicerList"/><br/>
                <xsl:if test="contains($juicerList, 'Champion')">
                    <xsl:text>- contains Champion</xsl:text><br/>
                </xsl:if>
                <xsl:if test="not(contains($juicerList, 'Champion'))">
                    <xsl:text>- does not contain Champion</xsl:text><br/>
                </xsl:if>
                <xsl:if test="contains($juicerList, 'Omega')">
                    <xsl:text>- contains Omega</xsl:text><br/>
                </xsl:if>
                <xsl:if test="not(contains($juicerList, 'Omega'))">
                    <xsl:text>- does not contain Omega</xsl:text><br/>
                </xsl:if>
                <xsl:if test="contains($juicerList, 'Ultrex')">
                    <xsl:text>- contains Ultrex</xsl:text><br/>
                </xsl:if>
                <xsl:if test="not(contains($juicerList, 'Ultrex'))">
                    <xsl:text>- does not contain Ultrex</xsl:text><br/>
                </xsl:if>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>