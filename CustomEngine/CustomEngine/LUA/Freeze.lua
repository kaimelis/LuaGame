function OnEnable()

end

function OnDisable()

end

function OnCreate()
	Freeze = Card.create("Freeze", "Assets/Card_Freeze.png")
	Card.show(Freeze, false)
	Info = {Damage = 0,Health=0,Mana = 5,Name="Freeze",Description = "Enemy frozen for one turn"}
end