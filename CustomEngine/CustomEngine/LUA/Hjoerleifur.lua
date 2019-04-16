function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Hjoerleifur = Card.create("Hjoerleifur", "Assets/Card_Damage.png")
	Card.show(Hjoerleifur, false)
	Info = {Damage = 2,Health=2,Mana = 2,Name="Hjoerleifur",Description = "I do Nothing"}
end