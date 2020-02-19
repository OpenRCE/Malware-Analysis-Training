<?xml version="1.0" standalone="no" ?>
<!--
   : mm2xbel.xsl
   : XSL stylesheet to convert from Mindmap to XBEL
   :
   : This code released under the GPL.
   : (http://www.gnu.org/copyleft/gpl.html)
   :
   : William McVey <wam@cisco.com>
   : September 11, 2003
   :
   : $Id: mm2xbel.xsl,v 1.1 2003/11/03 11:02:41 sviles Exp $
   :
  -->

<xsl:stylesheet version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:strip-space elements="*" /> 
	<xsl:output method="xml" indent="yes" encoding="UTF-8" />

	<xsl:template match="/map/node">
		<xbel version="1.0" folded="no">
			<title><xsl:value-of select="@TEXT" /></title>
			<xsl:for-each select="node">
				<xsl:call-template name="node"/>
			</xsl:for-each>
		</xbel>
	</xsl:template>

	<xsl:template name="node">
		<xsl:if test="string-length(@LINK) &gt; 0">
			<bookmark>
				<xsl:attribute name="href">
					<xsl:value-of select="@LINK" />
				</xsl:attribute>
				<title>
					<xsl:value-of select="@TEXT" /> 
				</title>
			</bookmark>
		</xsl:if>
		<xsl:if test="count(node) &gt;  0">
			<folder>
				<title>
					<xsl:value-of select="@TEXT" /> 
				</title>
				<xsl:for-each select="node">
					<xsl:call-template name="node"/>
				</xsl:for-each>
			</folder>
		</xsl:if>
		<xsl:if test="count(node) = 0">
			<xsl:for-each select="node">
				<xsl:call-template name="node"/>
			</xsl:for-each>
		</xsl:if>
	</xsl:template>

</xsl:stylesheet>
