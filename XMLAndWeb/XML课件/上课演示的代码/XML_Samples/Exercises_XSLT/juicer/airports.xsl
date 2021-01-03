<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:variable name="lcase" select="'abcdefghijklmnopqrstuvwxyz'"/>
    <xsl:variable name="ucase" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

    <xsl:template match="/" >
        <HTML>
            <HEAD>
                <TITLE>Electric Juicers</TITLE>
            </HEAD>
            <BODY>
                <xsl:for-each select="/airports/location">
                    <xsl:choose>
                        <xsl:when test="starts-with(.,'ICAO:')">
                            <xsl:text>ICAO = </xsl:text>
                            <xsl:variable name="icao" select="substring-after(., 'ICAO:')"/>
                            <xsl:value-of select="translate($icao, $lcase, $ucase)"/>
                            <BR/>
                        </xsl:when>
                        <xsl:when test="starts-with(.,'LatLon:')">
                            <xsl:text>LatLon = </xsl:text>
                            <xsl:variable name="latlon" select="substring-after(., 'LatLon:')"/>
                            <xsl:value-of select="translate($latlon, $lcase, $ucase)"/>
                            <BR/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>Data Error!  Data must be formatted as: ICAO: code, or LatLon: value</xsl:text>
                            <BR/>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:for-each>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>