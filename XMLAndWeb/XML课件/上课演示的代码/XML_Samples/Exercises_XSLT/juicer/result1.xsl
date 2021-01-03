<?xml version="1.0" encoding="UTF-8"?><xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:axsl="http://www.w3.org/1999/XSL/Transform/alias"><xsl:output method="xml"/><xsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/><xsl:namespace-alias stylesheet-prefix="axsl2" result-prefix="axsl"/><xsl:template match="/" xmlns:axsl2="http://www.w3.org/1999/XSL/Transform/alias2">
        <axsl:stylesheet version="1.0">
         
            <axsl:output method="xml"/>

            <axsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/>
            <axsl:namespace-alias stylesheet-prefix="axsl2" result-prefix="axsl"/>
           
            <xsl:variable name="self" select="document('Learn.xsl')"/>
            <xsl:copy-of select="$self//xsl:template[@match='/']"/>
 
            <xsl:apply-templates/>

        </axsl:stylesheet>
    </xsl:template><xsl:template match="FitnessCenter"/><xsl:template match="Member"/><xsl:template match="Name"/><xsl:template match="Phone"/><xsl:template match="Phone"/><xsl:template match="FavoriteColor"/><xsl:template match="Member"/><xsl:template match="Name"/><xsl:template match="Phone"/><xsl:template match="Phone"/><xsl:template match="FavoriteColor"/><xsl:template match="Member"/><xsl:template match="Name"/><xsl:template match="Phone"/><xsl:template match="Phone"/><xsl:template match="FavoriteColor"/></xsl:stylesheet>