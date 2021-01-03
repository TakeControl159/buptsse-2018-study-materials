<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:template match="/">
        <Members>
            <xsl:for-each select="//Member">
                <Name>
                    <xsl:value-of select="Name"/>
                </Name>
            </xsl:for-each>
        </Members>
    </xsl:template>

</xsl:stylesheet>