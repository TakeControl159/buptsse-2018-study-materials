<result> 
	{ 
		for $i in document("items.xml")/items/item_tuple 
		let $b := document("bids.xml")//bid_tuple[itemno = $i/itemno] 
		where contains($i/description,"Bicycle") 
		order by $i/itemno 
		return 
		<item_tuple> 
			{$i/itemno} 
			{$i/description} 
			<high_bid> 
				{ max ( for $c in $b/bid return xs:decimal($c) ) } 
			</high_bid> 
		</item_tuple> 
	} 
</result> 
(: Stylus Studio meta-information - (c) 2004-2005. Progress Software Corporation. All rights reserved.
<metaInformation>
<scenarios/><MapperMetaTag><MapperInfo srcSchemaPathIsRelative="yes" srcSchemaInterpretAsXML="no" destSchemaPath="" destSchemaRoot="" destSchemaPathIsRelative="yes" destSchemaInterpretAsXML="no"/><MapperBlockPosition></MapperBlockPosition></MapperMetaTag>
</metaInformation>
:)