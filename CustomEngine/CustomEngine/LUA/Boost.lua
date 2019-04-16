function OnEnable()
	Card.boost(2);
end

function OnDisable()
	
end

function OnCreate()
	Boost = Card.create("Boost", "Assets/Card_Boost.png")
	Card.show(Boost, true)
	Info = {Damage = 0,Health=0,Mana = 5,Name="Boost", Description = "Adds +2 Damage To every attack card"}
end