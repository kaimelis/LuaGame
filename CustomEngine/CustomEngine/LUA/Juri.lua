function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Juri = Card.create("Juri", "Assets/Card_Damage.png")
	Card.show(Juri, true)
	Info = {Damage = 5,Health=1,Mana = 4,Name="Juri",Description = "I do Nothing"}
end