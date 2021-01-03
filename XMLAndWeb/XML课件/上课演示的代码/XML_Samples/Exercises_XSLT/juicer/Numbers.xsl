<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Check Numbers</TITLE>
            </HEAD>
            <BODY>
                <xsl:text>All numbers in the list are less than or equal to 100: </xsl:text> 
                <xsl:variable name="result">
                    <xsl:call-template name="AllLessThan100">
                         <xsl:with-param name="numberList" select="NumberList/Number"/>
                    </xsl:call-template>
                </xsl:variable>
                <xsl:value-of select="$result"/>
            </BODY>
        </HTML>
    </xsl:template>

    <xsl:template name="AllLessThan100">
        <xsl:param name="numberList"/>
        <xsl:choose>
            <xsl:when test="not($numberList)">
                <xsl:text>true</xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="$numberList[1] &gt; 100">
                        <xsl:text>false</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:call-template name="AllLessThan100">
                            <xsl:with-param name="numberList" select="$numberList[position() &gt; 1]"/>
                        </xsl:call-template>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

</xsl:stylesheet>