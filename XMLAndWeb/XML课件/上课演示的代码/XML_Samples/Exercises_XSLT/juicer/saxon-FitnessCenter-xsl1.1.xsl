<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.1">
 
    <xsl:output method="xml"/>

    <xsl:template match="FitnessCenter">
        <FitnessCenter>
            <PlatinumMembers href="platinum.xml"/>
            <xsl:document href="platinum.xml">
                <PlatinumMembers>
                    <xsl:for-each select="Member[@level='platinum']">
                        <xsl:copy-of select="."/>
                    </xsl:for-each>
                </PlatinumMembers>
            </xsl:document>
            <GoldMembers href="gold.xml"/>
            <xsl:document href="gold.xml">
                <GoldMembers>
                    <xsl:for-each select="Member[@level='gold']">
                        <xsl:copy-of select="."/>
                    </xsl:for-each>
                </GoldMembers>
            </xsl:document>
        </FitnessCenter>
    </xsl:template>

</xsl:stylesheet>