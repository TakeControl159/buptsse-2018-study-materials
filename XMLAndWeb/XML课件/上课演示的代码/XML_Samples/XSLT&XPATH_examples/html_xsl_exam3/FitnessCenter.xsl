<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Welcome</TITLE>
            </HEAD>
            <BODY bgcolor="{/FitnessCenter/Member/FavoriteColor}">
                Welcome <xsl:value-of select="/FitnessCenter/Member/Name"/>!
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>