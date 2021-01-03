<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xalan="http://org.apache.xalan.xslt.extensions.Redirect"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:template match="FitnessCenter">
        <FitnessCenter>
            <PlatinumMembers href="platinum.xml"/>
            <xalan:write file="platinum.xml">
                <PlatinumMembers>
                    <xsl:for-each select="Member[@level='platinum']">
                        <xsl:copy-of select="."/>
                    </xsl:for-each>
                </PlatinumMembers>
            </xalan:write>
            <GoldMembers href="gold.xml"/>
            <xalan:write file="gold.xml">
                <GoldMembers>
                    <xsl:for-each select="Member[@level='gold']">
                        <xsl:copy-of select="."/>
                    </xsl:for-each>
                </GoldMembers>
            </xalan:write>
        </FitnessCenter>
    </xsl:template>

</xsl:stylesheet>