<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Electric Juicers</TITLE>
            </HEAD>
            <BODY>
                <xsl:for-each select="/juicers/juicer">
                    <xsl:variable name="juicerName" select="name"/>
                    <xsl:variable name="isElectric" select="@electric"/>
                    <xsl:if test="$isElectric='true'">
                        This juicer is electric: <xsl:value-of select="$juicerName"/><br/>
                    </xsl:if>
                </xsl:for-each>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>