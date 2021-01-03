<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon"
                version="1.0">
 
    <xsl:output method="xml"/>
    <xsl:variable name="tests" select="document('checkFitnessCenter.xml')"/>
 
    <xsl:template match="/">
        <xsl:variable name="here" select="."/>
        <FitnessCenter-results>
            <xsl:for-each select="$tests//xpath">
                <result>
                    <xsl:variable name="xpath" select="."/>
                    <xsl:value-of select="$xpath"/>
                    <xsl:for-each select="$here">
                        <xsl:choose>
                            <xsl:when test="saxon:evaluate($xpath)">
                                <xsl:text> SUCCEEDED</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text> FAILED</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:for-each>
                    <xsl:text>
</xsl:text>
                </result>
            </xsl:for-each>
        </FitnessCenter-results>
    </xsl:template>


</xsl:stylesheet>